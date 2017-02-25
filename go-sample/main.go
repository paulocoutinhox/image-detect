package main

/*
#cgo pkg-config: opencv
#include "/Users/paulo/Developer/workspaces/cpp/image-detect/lib/include/image-detect.h"
*/
import "C"
import (
	"log"
	"os"
)

func main() {
	imageDetectHome := os.Getenv("IMAGE_DETECT_HOME")

	screenImagePath := imageDetectHome + "/extras/images/screen.png"
	detectImagePath := imageDetectHome + "/extras/images/detect.png"
	outputImagePath := imageDetectHome + "/extras/images/diff.png"

	result := C.process(C.String(screenImagePath), C.String(detectImagePath), C.String(outputImagePath))
	log.Print(result)
}
