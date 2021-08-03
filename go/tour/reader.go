package main

import "golang.org/x/tour/reader"

type MyReader struct{}

// TODO: Add a Read([]byte) (int, error) method to MyReader.
func (r MyReader) Read(b []byte) (int, error) {
	var i = 0
	var cnt = 0
	for i = range b {
		b[i] = 'A'
		cnt++
	}
	return cnt, nil
}

func main() {
	reader.Validate(MyReader{})
}
