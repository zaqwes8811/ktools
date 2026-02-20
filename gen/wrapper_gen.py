from pycparser import c_parser, c_ast, parse_file

# # Parse the C file
# ast = parse_file('my_file.c', use_cpp=False)

# # Traverse the AST to find function definitions
# for ext in ast.ext:
#     if isinstance(ext, c_ast.FuncDef):
#         print(f"Function Name: {ext.decl.name}")
#         # You can further process ext.body to get the function's code


ignore = [
    'decon_get_ewr_cycle',
    'decon_get_vfp_th',
    'decon_reg_set_bpc_and_dither',
    'decon_reg_set_ewr_control',
    'decon_reg_set_ewr_enable',
    'decon_reg_set_ewr_timer',
    'decon_reg_set_vfp_threshold',
    'decon_reg_update_ewr_control',
]

with open('ctags_out.c') as f:
    ls = f.readlines()
    for l in ls:
        l = l.strip()

        found = False

        for i in ignore:
            if i in l:
                found = True
                break

        if found:
            print("Skip: ", l)
            continue

        # if 'decon_reg_get_devdata' not in l:
        #     continue

        if l[-1] == ',':
            # l += " early_term x)"
            print("Skip: ", l)
            continue

        if '[' in l:
            print("Skip: ", l)
            continue



        l = l.replace("{", '').replace("}", '').strip()

        l = l.replace("inline", "")
        l = l.replace("  ", " ")

        lz = l.split("{")[0]
        l = lz

        #l = l.replace("(", " ")
        #l = l.replace(" ", ", ")
        #l = l.replace(",,", ",")

        ll = l.split("(")
        kk = ll[-1].replace(")", "")
        zz = kk.split(", ")

        args = []
        for z in zz:
            z = z.replace("*", "* ")
            index_of_last_space = z.rfind(' ')
            y = z[:index_of_last_space]
            args.append(y)
        args_part = ", ".join(args)
        args_part1 = "(" + args_part + ")"

        sign = ll[0]

        if 'static' in sign:
            spl = sign.replace('static', '').replace('*', '* ').strip().split(" ")
            rv_sig = [' '.join(spl[:-1]), spl[-1]]
            s = rv_sig + args

            recored = "STATIC_WRAP(" + ", ".join(s) + ");"
            print(recored)
            # print(l)
            # print('sign: ', sign)
        else:
            spl = sign.replace('static', '').replace('*', '* ').strip().split(" ")
            rv_sig = [' '.join(spl[:-1]), spl[-1]]
            s = rv_sig + args

            recored = "WRAP(" + ", ".join(s) + ");"
            print(recored)

        # print("[] ", sign + args_part1)
        # print("  ", l)
