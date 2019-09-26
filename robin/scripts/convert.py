#!/usr/bin/env python3
from PIL import Image
import numpy

imgFile = "new_file.png"

import numpy
import PIL

img = PIL.Image.open(imgFile).convert("1")

imgarr = numpy.array(img) 

numpy.savetxt("converted.txt", imgarr, fmt='%i', delimiter="")



#from PIL import Image
#import PIL.ImageOps    

#image = Image.open('your_image.png')
#if image.mode == 'RGBA':
#    r,g,b,a = image.split()
#    rgb_image = Image.merge('RGB', (r,g,b))

#    inverted_image = PIL.ImageOps.invert(rgb_image)

#    r2,g2,b2 = inverted_image.split()

#    final_transparent_image = Image.merge('RGBA', (r2,g2,b2,a))

#    final_transparent_image.save('new_file.png')

#else:
#    inverted_image = PIL.ImageOps.invert(image)
#    inverted_image.save('new_name.png')
