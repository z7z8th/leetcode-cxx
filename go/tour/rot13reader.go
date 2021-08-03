package main

import (
	"io"
	"os"
	"strings"
)

type rot13Reader struct {
	r io.Reader
}

func rot13(b byte) byte {
	if 'A' <= b && b <= 'M' || 'a' <= b && b <= 'm' {
		b += 13
	} else if 'N' <= b && b <= 'Z' || 'n' <= b && b <= 'z' {
		b -= 13
	}

	return b
}

func (r13r rot13Reader) Read(b []byte) (int, error) {
	var i = 0
	n, err := r13r.r.Read(b)
	if err != nil {
		return n, err
	}
	for i = range b[:n] {
		b[i] = rot13(b[i])
	}
	return n, nil
}

func main() {
	s := strings.NewReader("Lbh penpxrq gur pbqr!")
	r := rot13Reader{s}
	io.Copy(os.Stdout, &r)
}
