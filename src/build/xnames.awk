# Generate a portable UC3 symbol manifest for self-importing UCRI.
# Addresses from nm are deliberately discarded: dlsym/GetProcAddress resolves
# each symbol in the running process, so PIE, ASLR, and 64-bit pointers are safe.
BEGIN { print "UC3 AUTO" }
/XTrace|XEntry|XFunction|XType|XNTable|XClass|XModule|XTemplateFun|uc_global|uc_std|uc_eval_method|uc_ucri_init|ucri_instruction_counter/ {
    symbol = $NF
    if ($0 !~ /_Rb_tree/ && !seen[symbol]++) print symbol
}
