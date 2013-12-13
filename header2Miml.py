#!/usr/bin/python

#     Assumptions:
#         - only parses extern functions
#         - init/final functions only detected with "initialize" and "finalize" in name
#         - any non-init/final functions with "initialize" or "finalize" aren't included
#         - only data types recognized are [const|unsigned] [int|char]
#         - variable names not defined are replaced by ARG# variable name

import sys, re, os
import argparse
import yaml

if __name__ == '__main__':
    argparser = argparse.ArgumentParser()
    argparser.add_argument('header', help='C header to convert to a MIML module')
    argparser.add_argument('modulename', nargs='?', help='Name of the MIML module file. Defaults to Header name')
    args = argparser.parse_args()

    if not args.header.endswith('.h'):
        print("Error: Input file not a .h file.")
        sys.exit(-1)
    basename = os.path.basename(args.header)[:-2]  # strip .h

    header = basename + '.h'
    objfile = basename + '.o'

    if not args.modulename:
        outputfile = basename + '.miml'
    elif args.modulename.endswith('.miml'):
        outputfile = args.modulename
    else:
        print("Error: Output file not a .miml file.")
        sys.exit(-1)

    try:
        with open(args.header, 'r') as f:
            codeLines = f.readlines()
    except IOError as e:
        print("I/O error({0}): Input header file --> {1}".format(e.errno, e.strerror))
        sys.exit(-1)

    output = {'include': header, 'object': objfile, 'senders': {}, 'receivers': {}}

    foundInit = 0
    foundFinal = 0
    foundSenders = 0
    foundReceivers = 0

    def xstr(s):
        if s is None:
            return ''
        return str(s)

    for item in codeLines:
        # match = re.match( r'[\s]*(extern[\s]+)?([\w]+[\s]+)([\w_-]+)[\s]*\((.*)\).*', item.strip('\n'), re.M|re.I)
        match = re.match(r'[\s]*(extern[\s]+)?([\w]+[\s]+)([\w_-]+)[\s]*\((.*)\)[\s]*;[\s]*(\/\/[\s]*\[[\s]*miml[\s]*:[\s]*(init|final|sender|receiver)[\s]*\])?.*', item.strip('\n'), re.M | re.I)
        if match:
            mimlType = match.group(6)
            if(mimlType == "init"):
                output['init'] = str(match.group(3)) + "();"
                foundInit += 1
                continue

            if(mimlType == "final"):
                output['final'] = str(match.group(3)) + "();"
                foundFinal += 1
                continue

            content = match.group(4).split(',')
            counter = 0

            argVals = []
            for item2 in content:
                counter += 1
                match2 = re.match(r'[\s]*((const|unsigned)[\s]+)?(.*)[\s]*(\*)?([\s]*([\w_-]+)[\s]*)?', item2, re.M | re.I)
                if match2:
                    argType = xstr(match2.group(1)) + xstr(match2.group(3)) + xstr(match2.group(4))
                    argName = match2.group(6)
                    if argName is None:
                        argName = "ARG" + str(counter)

                    argVals.append([argName, argType.strip()])

            funcName = str(match.group(3))
            if (mimlType == "receivers"):
                output['receiver'][funcName] = argVals
                foundReceivers += 1
            elif (mimlType == "sender"):
                output['senders'][funcName] = argVals
                foundSenders += 1

    try:
        with open(outputfile, 'w') as fout:
            yaml.dump(output, fout)
    except IOError as e:
        print("I/O error({0}): Output Miml file --> {1}".format(e.errno, e.strerror))
        sys.exit(-1)

    print("\n " + args.header + "  ->  " + outputfile)
    print("======================================================")
    print(" Init\tFinal\tSenders\t  Receivers                     ")
    print("------------------------------------------------------")
    print(" " + str(foundInit) + "\t" + str(foundFinal) + "\t" + str(foundSenders) + "\t  " + str(foundReceivers))
