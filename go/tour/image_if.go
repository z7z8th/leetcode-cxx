package main

import (
	"image"
	"image/color"

	"golang.org/x/tour/pic"
)

type Image struct{
	w, h int
    //ColorModel() color.Model
    //Bounds() Rectangle
    //At(x, y int) color.Color
}

func (i Image) ColorModel() color.Model {
	return color.RGBAModel
}

func (i Image) Bounds() image.Rectangle {
	return image.Rect(0, 0, i.w, i.h)
}

func (i Image) At(x, y int) color.Color {
	return color.RGBA{uint8(x^y), uint8(x^y), 255, 255}
}

func main() {
	m := Image{100, 100}
	pic.ShowImage(m)
}
