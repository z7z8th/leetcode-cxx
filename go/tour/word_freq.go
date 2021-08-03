package main

import (
	"golang.org/x/tour/wc"
	"strings"
)

func WordCount(s string) map[string]int {
	var ss = strings.Split(s, " ")
	ret := make(map[string]int)
	var v string
	for _, v = range ss {
		ret[v]++
	}
	return ret
}

func main() {
	wc.Test(WordCount)
}
