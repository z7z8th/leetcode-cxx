package main

import "golang.org/x/tour/pic"

func Pic(dx, dy int) [][]uint8 {
	var i, j int = 0, 0
	var ret [][]uint8= make([][]uint8, dy)
	for i, _ = range ret {
	   ret[i] = make([]uint8, dx)
	   for j = range ret[i] {
	   		ret[i][j] = uint8((i^j))
	   }
	}
	return ret
}

func main() {
	pic.Show(Pic)
}
