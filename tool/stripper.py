from os import path

import sys;


def main():
    if len(sys.argv) != 5:
        print "usage: %s TARGET_FILE PATTERN_START PATTERN_END OUTPUT_FILE" % \
              (path.basename(sys.argv[0]))
        return

    filename = sys.argv[1]
    pattern_start = sys.argv[2]
    pattern_end = sys.argv[3]
    output_filename = sys.argv[4]

    print "Filename:         " + filename
    print "Pattern-start:    \"%s\"" % pattern_start
    print "Pattern-end:      \"%s\"" % pattern_end
    print "Output-filename:  " + output_filename

    with open(filename, "r") as f:
        lines = f.readlines()

    with open(output_filename, "w") as f:
        stripping = False

        for line in lines: 
            if stripping:
                if line.startswith(pattern_end):
                    stripping = False 
            else:
                if line.startswith(pattern_start):
                    stripping = True
                else:
                   f.write(line) 


if __name__ == "__main__":
    main()
