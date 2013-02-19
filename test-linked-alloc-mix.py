from subprocess import Popen, PIPE, call

# Set up input
if call(["ln", "-sf", "test-in1.txt", "cardrd.dev"]) != 0:
        print "FAIL"
        print "Unable to set up input"
        exit(1)

# Build app
if call(["make", "mix-linked_alloc"]) != 0:
        print "FAIL"
        print "Unable to build app"
        exit(1)

# Run app
if call(["./mix-linked_alloc"]) != 0:
        print "FAIL"
        print "Unable to run app"
        exit(1)

# Compare output with expected
# TODO: Make this into a function
out = Popen(["diff", "out1.txt", "out1.txt"], stdout=PIPE).communicate()[0]

if out != '':
        print "FAIL"
        print out
else:
        print "PASS"

