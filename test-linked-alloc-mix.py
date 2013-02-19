from subprocess import Popen, PIPE, call

# Set up input
if call(["ln", "-sf", "test-in1.txt", "cardrd.dev"]) != 0:
        print "FAIL"
        print "Unable to set up input"
        exit(1)

# Run app
if call(["make", "run-mix-linked_alloc"]) != 0:
        print "FAIL"
        print "Unable to build app"
        exit(1)

# Compare output with expected
# TODO: Make this into a function
# TODO: Figure out how to run mixvm against local "devices"
out = Popen(["diff", "out1.txt", "/home/rjose/.mdk/printer.dev"], stdout=PIPE).communicate()[0]

if out != '':
        print "FAIL"
        print out
else:
        print "PASS"

