/* os.cpp
 * All miscelaneous OS-dependent stuff goes here.
 * UnderC C++ interpreter
 * Steve Donovan, 2001
 * This is GPL'd software, and the usual disclaimers apply.
 * See LICENCE
*/

#include "os.h"

#ifdef _WIN32
#include "directcall.h"
#include <windows.h>

// unfortunately, _stat does not work on Win32?
// certainly don't seem to get an accurate fractional time.
//ASK: Does this function need a __int64 return type?
long get_file_time(const char *file)
{
  FILETIME at; // hahmm
  OFSTRUCT ofs;
  void *hFile = (void *)OpenFile(file, &ofs, OF_READ);
  GetFileTime(hFile,NULL,NULL,&at);
  CloseHandle(hFile);
  __int64 *f = (__int64 *)&at;
  (*f) /= 100000;
  long val = (long)*f;
  return val;
}

Handle load_library(const char *name)
{
// *add 1.2.0 Support for $caller under Win32
  if (name==NULL) return get_process_handle();
  return (Handle) LoadLibrary(name);
}

void free_library(Handle h)
{
  FreeLibrary((HINSTANCE)h);
}

void *get_proc_address(Handle h, const char *name)
{
 // *add 1.2.0 if there's a supplied .imp file, we use that
 // *add 1.2.2 (Eric) if it's not in the imp file, try the DLL...
 // *add 1.2.5 imp file may contain _absolute_ addresses
    if (Builtin::using_ordinal_lookup()) {
        uintptr_t ordn = Builtin::lookup_ordinal(name);
        if (ordn!=0) {	  
          if (Builtin::lookup_is_ordinal())
	         name = reinterpret_cast<const char *>(ordn);
  // and pass through
	      else return reinterpret_cast<void *>(ordn);
	}
    }
  void *proc = (void*)GetProcAddress((HINSTANCE)h,name);
  if (!proc) {
    const char *alias = Builtin::lookup_symbol_alias(name);
    if (alias) proc = (void*)GetProcAddress((HINSTANCE)h,alias);
  }
  return proc;
}

Handle get_process_handle()
{
  return (Handle) GetModuleHandle(NULL);
}

void *alloc_executable(const void *code, size_t size)
{
  if (size == 0) return NULL;
  void *page = VirtualAlloc(NULL,size,MEM_COMMIT | MEM_RESERVE,PAGE_READWRITE);
  if (page == NULL) return NULL;
  memcpy(page,code,size);
  DWORD previous;
  if (!VirtualProtect(page,size,PAGE_EXECUTE_READ,&previous)) {
    VirtualFree(page,0,MEM_RELEASE);
    return NULL;
  }
  FlushInstructionCache(GetCurrentProcess(),page,size);
  return page;
}

#else
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "directcall.h"

char *itoa(int val, char *buff, int)
{
  sprintf(buff,"%d",val);
  return buff;
}

long get_file_time(const char *filename)
{
 struct stat st;
 stat(filename,&st);
 return st.st_mtime;
}

void *alloc_executable(const void *code, size_t size)
{
  if (size == 0) return NULL;
  void *page = mmap(NULL,size,PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
  if (page == MAP_FAILED) return NULL;
  memcpy(page,code,size);
  if (mprotect(page,size,PROT_READ | PROT_EXEC) != 0) {
    munmap(page,size);
    return NULL;
  }
  return page;
}

// *ch 1.2.9 patch 
#ifdef __BEOS__
#include <OS.h>
#include <image.h>
#include <string.h>
/* XXX:FIXME: make it all native */
#include <dlfcn.h>

Handle get_process_handle()
{
 image_info ii;
 int32 cookie = 0;
 while (get_next_image_info(0, &cookie, &ii) >= B_OK) {
  if (ii.type == B_APP_IMAGE)
   return (Handle) ii.id;
 }
 return (Handle) 0;
}

Handle load_library(const char *name)
{
 image_info ii;
 int32 cookie = 0;
 /* XXX: needs a better euristic */
 while (get_next_image_info(0, &cookie, &ii) >= B_OK) {
  printf("img: %s\n", ii.name);
  if (strstr(ii.name, name)) {
   puts("match");
   return (Handle)ii.id;
  }
 }
 printf("dlopen(%s)\n", name);
 /* not yet loaded: load it ourselves */
 return dlopen(name, RTLD_LAZY);
}

void free_library(Handle h)
{
 image_info ii;
 image_id img = (image_id)h;
 printf("free_library(%08lx)\n", h); /* XXX:DBG */
 if (get_image_info(img, &ii) == B_OK) {
  if (ii.type == B_ADD_ON_IMAGE)
   unload_add_on(img);
 }
}

void *get_proc_address(Handle h, const char *name)
{
 void *sym;
 image_id img = (image_id)h;
 printf("get_proc_address(%08lx, %s)\n", h, name); /* XXX:DBG */
  // Legacy Linux manifests may contain absolute addresses. UC3 manifests
  // fall through to process-symbol lookup.
 if (Builtin::using_ordinal_lookup()) {
   uintptr_t ordn = Builtin::lookup_ordinal(name);
   if (ordn!=0) {
    return reinterpret_cast<void *>(ordn);
   }
 }
 if (get_image_symbol(img, name, B_SYMBOL_TYPE_ANY, &sym) < B_OK) {
  const char *alias = Builtin::lookup_symbol_alias(name);
  if (!alias || get_image_symbol(img, alias, B_SYMBOL_TYPE_ANY, &sym) < B_OK)
   return NULL;
 }
 return sym;
}

#else /* __BEOS__ */
#include <dlfcn.h>

Handle get_process_handle()
{
   return NULL;
}

Handle load_library(const char *name)
{
  return dlopen(*name!=0 ? name : NULL,RTLD_LAZY);
}

void free_library(Handle h)
{
  dlclose(h);
}

void *get_proc_address(Handle h, const char *name)
{
  // *add 1.2.4 In the case of Linux, the .IMP file actually contains
  // absolute addresses.
 if (Builtin::using_ordinal_lookup()) {
   uintptr_t ordn = Builtin::lookup_ordinal(name);
   if (ordn!=0) {	  
     return reinterpret_cast<void *>(ordn);
   }
  } 
 void *proc = dlsym(h,name);
 if (!proc) {
   const char *alias = Builtin::lookup_symbol_alias(name);
   if (alias) proc = dlsym(h,alias);
 }
 return proc;
}

#endif /* __BEOS__ */

#endif /* _WIN32 */

 
