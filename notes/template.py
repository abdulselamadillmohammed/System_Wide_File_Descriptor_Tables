
## this will take in postional arguments


# Define in the background what these taskes do:
"""
Ie, write in function documentation
"""
argv = ["--per-process", 
        "--systemWide",
        "--Vnodes",
        "--composite",
        "--summary",

        # On threshold check if it is a number
        "--threshold=X"
        ]
argc = len(argv)

# Easier, hold something for flagged 
# another for positonal
set_arguments = [0] * argc

def parser(argc: int, argv: str) -> None:
    for i in range(argc):
        set


parser(argc, argv)


# Argv acts as a list of values which I must extract from via positons
# ./process
#--per-process
#--systemWide

def main():
    parser(argc, argv)
    # if the flagged aguments sum to 0, then set them to which
    # ever default version you want
