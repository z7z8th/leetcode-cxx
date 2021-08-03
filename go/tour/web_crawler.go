package main

import (
	"fmt"
	"sync"
	"time"
)

type Fetcher interface {
	// Fetch returns the body of URL and
	// a slice of URLs found on that page.
	Fetch(url string) (body string, urls []string, err error)
}

type PageCaches struct {
	visited map[string]int
	lock sync.Mutex
}

var pcc = PageCaches {visited: make(map[string]int)}

func CrawlOne(url string, fetcher Fetcher) (string, []string, error) {
	pcc.lock.Lock()
	vcnt := pcc.visited[url]
	if vcnt == 0 {
		pcc.visited[url]++
	}
	pcc.lock.Unlock()

	if vcnt > 0 {
		return "", nil, nil
	}
	fmt.Println("One > ", url)
	body, urls, err := fetcher.Fetch(url)

	if err != nil {
		fmt.Println(err)
		return "", nil, nil
	}
	fmt.Printf("found: %s %q\n", url, body)
	return body, urls, err
}

// Crawl uses fetcher to recursively crawl
// pages starting with url, to a maximum of depth.
func Crawl(url string, depth int, fetcher Fetcher) {
	// TODO: Fetch URLs in parallel.
	// TODO: Don't fetch the same URL twice.
	// This implementation doesn't do either:
	if depth <= 0 {
		return
	}
	_, urls, _ := CrawlOne(url, fetcher)
	for _, u := range urls {
		// fmt.Println("go >", u)
		go Crawl(u, depth-1, fetcher)
	}
	return
}

func main() {
	// ch := make(chan string)
	Crawl("https://golang.org/", 4, fetcher)
	time.Sleep(time.Second)
}

// fakeFetcher is Fetcher that returns canned results.
type fakeFetcher map[string]*fakeResult

type fakeResult struct {
	body string
	urls []string
}

func (f fakeFetcher) Fetch(url string) (string, []string, error) {
	if res, ok := f[url]; ok {
		return res.body, res.urls, nil
	}
	return "", nil, fmt.Errorf("not found: %s", url)
}

// fetcher is a populated fakeFetcher.
var fetcher = fakeFetcher{
	"https://golang.org/": &fakeResult{
		"The Go Programming Language",
		[]string{
			"https://golang.org/pkg/",
			"https://golang.org/cmd/",
		},
	},
	"https://golang.org/pkg/": &fakeResult{
		"Packages",
		[]string{
			"https://golang.org/",
			"https://golang.org/cmd/",
			"https://golang.org/pkg/fmt/",
			"https://golang.org/pkg/os/",
		},
	},
	"https://golang.org/pkg/fmt/": &fakeResult{
		"Package fmt",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
	"https://golang.org/pkg/os/": &fakeResult{
		"Package os",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
}
