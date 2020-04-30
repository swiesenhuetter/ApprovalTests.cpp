<a id="top"></a>

# Custom Comparators

toc

## Default Behaviour

When Approval Tests compares the "expected" and "approved" files to verify that they are the same, it reads both files, one character at a time, and tests if their contents are identical.

Note that it **ignores differences in line endings**, to ensure that files written on Windows will match thos written on Unix, and vice versa.

In almost all uses of Approval Tests, this behaviour works well.

## Registering a custom comparator

### Overview

This section shows how to customise the way that file contents are compared in Approval Tests.

Real-world example scenario:

* Suppose you are approving image files, and for some reason, there are sometimes tiny differences in the red, green or blue colour values. Or perhaps on some test environments, the images are written 24-bit files, and on others they are 32-bit.
* You know that no human would ever be able to detect these tiny differences visually, so you want Approval Tests to treat files with only these tiny differences as equivalent.
* But Approval Tests doesn't know this: it just sees a 24-bit .png file and a 32-bit one as having different content.
* So you wish to customise Approval Tests to read the colour values in the two files, and ignore any tiny differences in these values. 

There are two steps needed to get Approval Tests to use a custom file comparison:

1. A custom implementation of the `ApprovalComparator` interface, that reads two files and reports if they are equivalent
2. A call to `FileApprover::registerComparator()`, supplying an instance of the custom comparator, and the file extension it should be used for. 

### Example Code

In this trivial example, we want to treat two files as matching if their contents are the same length.

First, we write our custom `ApprovalComparator` implementation:

snippet: create_custom_comparator

Then we call `FileApprover::registerComparator()` to tell Approval Tests to use `LengthComparator` to compare all files with extension `.length`. This customisation will last for the rest of the test run, and we would typically put this in our `main.cpp`.

snippet: use_custom_comparator

The return value is ["Disposable"](/doc/DisposableObjects.md#top), meaning it will restore the original comparator when the object destructs. Because of this, if you do not store the result in a variable, it will immediately undo itself by the end of the line.

---

[Back to User Guide](/doc/README.md#top)
