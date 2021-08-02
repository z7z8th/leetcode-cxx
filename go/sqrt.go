package main

import (
	"fmt"
	"math"
)

func step(z, x float64) float64 {
	return z-(z*z - x)/(2*z)
}

func Sqrt(x float64) float64 {
	if x < 0 {
		return Sqrt(-x)
	}
	var z,nextz float64 = 0,0
	for z=x/2; ; z = nextz {
		nextz = step(z,x)
		if math.Abs(nextz - z) < 0.00001 {
			return z
		}
	}
}

func main() {
	fmt.Println(Sqrt(2))
	fmt.Println(Sqrt(0.6))
	fmt.Println(Sqrt(-4))
}
