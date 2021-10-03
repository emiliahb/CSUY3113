## Submission
**Emilia Budzikowski-- eb3303**

## Files
**source.cpp**: driver code for using the functionality of MyImageClass

**MyImageClass.h**: contains the code for MyImageClass

**.ppm files**: results of running various operations on the given ppm files

## The Code
**MyImageClass.h only handles P3 image files!** I attempted trying to handle P6 as well, and a few artifacts from that remain in the comments, just to attest to that, but ultimately was unable to come up with a functional solution. Otherwise, all functionality that was mentioned in the assignment (outside of alpha compositing) has been implemented. In regards to the mirrorX() function, I interpreted that as a mirroring of the data within the rows (X axis) of the image data, and not mirroring over the X axis. I wasn't sure if this was correct.

**In regards to addition:** I did both + and +=, but my results were not the same as was shown in the assignment specifications. I could not figure out what the issue was. I added pixel-by-pixel for the + operator, and averaged for +=. I read the assignment and then reread and then reread again and still couldn't quite figure out what my issue was. Looking at the image result from the assignment, it looks like the white of the Tandon image was treated as if it were transparent, since it did not affect those parts of the Mandrill image. I couldn't figure out how the interaction in the rest of the image worked, so I left my solution as-is, so that I would have *some* solution.

In order to check the functionality of MyImageClass, you should place MyImageClass.h and source.cpp in the same folder, and then compile and run source.cpp. The execution takes a few minutes, but afterwards, all of the resulting images should end up in the same folder as source.cpp and MyImageClass.h.

## Additional Thoughts
I'm not sure if it was just me with this issue, but I found that there was a lot of room for interpretation in the assignment specifications. Certain parts of the assignment were fairly unclear. I had trouble understanding the addition operator, as mentioned earlier, but I also was unsure as to what part of the assignment counted as extra credit. Alpha Compositing came right before the "Optional Tasks" section, and that section said "this task," so I assumed that it referred to the previous task. If the line from "Optional Tasks" was in the "Alpha Compositing" section, I feel that this would have been much more clear, and would not leave any room for misinterpretation.
