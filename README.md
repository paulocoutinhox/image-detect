# Image Detect

Detect a minor image over a bigger image, ex: a button inside the phone screenshot and return positions in JSON format.

The result image (diff image) is optional, you can ommit it to only return the result in JSON.  

Thre is a "threshold" param to you specify the level of relevance of the image inside other.  

# Get started

To compile and install:  
  
> make  
> make install  

# How to use

> image-detect ./extras/images/screen.png ./extras/images/detect.png ./extras/images/diff.png  

# Tests

I have made some tests, use make to run it:

1. make run-sample
2. make run-sample-double-detect
3. make run-sample-no-detect

# JSON returned (example)

If success:

> {"success": true, "message": "found", "data": {"list": [{"x1": 50, "y1": 188, "x2": 212, "y2": 362}, {"x1": 50, "y1": 422, "x2": 212, "y2": 596}]}}

If any problem, like not-found:

> {"success": false, "message": "not-found"}

# C++ sample

You can get the C++ sample program in "main.cpp" file.

# Result on double detect sample

** Image to detect: ** 

![Detect](https://github.com/prsolucoes/image-detect/raw/master/extras/images/detect.png "Detect")

** Inside image: ** 

![Screen](https://github.com/prsolucoes/image-detect/raw/master/extras/images/screen-double.png "Screen")

** Diff image: ** 

![Diff](https://github.com/prsolucoes/image-detect/raw/master/extras/images/diff-screen-double.png "Diff")

# Author WebSite

> http://www.pcoutinho.com