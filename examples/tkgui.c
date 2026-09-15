#include <stdio.h>

/* Import only the small Tcl/Tk API surface used by this example. */
#lib libtcl.so
extern "C" {
void Tcl_FindExecutable(const char *argv0);
void *Tcl_CreateInterp(void);
int Tcl_Init(void *interp);
int Tcl_Eval(void *interp, const char *script);
char *Tcl_GetStringResult(void *interp);
void Tcl_DeleteInterp(void *interp);
void Tcl_Finalize(void);
}
#lib

#lib libtk.so
extern "C" {
int Tk_Init(void *interp);
}
#lib

int report_tcl_error(void *interp, const char *operation)
{
    fprintf(stderr, "%s: %s\n", operation, Tcl_GetStringResult(interp));
    return 1;
}

int main(int argc, char **argv)
{
    Tcl_FindExecutable(argv[0]);
    void *interp = Tcl_CreateInterp();
    if (interp == 0) {
        fprintf(stderr, "Could not create a Tcl interpreter.\n");
        return 1;
    }
    if (Tcl_Init(interp) != 0)
        return report_tcl_error(interp, "Tcl_Init failed");
    if (Tk_Init(interp) != 0)
        return report_tcl_error(interp, "Tk_Init failed");

    const char *ui =
        "wm title . {UnderC Tk Example}; "
        "button .close -text {Close window} "
        "-command {destroy .; set ::window_closed 1}; "
        "pack .close -padx 40 -pady 30; "
        "vwait ::window_closed";
    int status = Tcl_Eval(interp, ui);
    if (status != 0) report_tcl_error(interp, "Tk event loop failed");
    Tcl_DeleteInterp(interp);
    Tcl_Finalize();
    return status == 0 ? 0 : 1;
}
