package main

import (
	"fmt"
	"sync"
)

type Fetcher interface {
	// Fetch returns the body of URL and
	// a slice of URLs found on that page.
	Fetch(url string) (body string, urls []string, err error)
}

type PageCaches struct {
	visited map[string]int
	lock sync.Mutex
	wg sync.WaitGroup
}

type CrawlReq struct {
	url string
	depth int
	main bool
}

var pcc = PageCaches {visited: make(map[string]int)}

func Visited(url string, incr bool) bool {
	pcc.lock.Lock()
	vcnt := pcc.visited[url]
	if vcnt == 0 && incr {
		pcc.visited[url]++
	}
	pcc.lock.Unlock()

	return vcnt > 0
}

// Crawl uses fetcher to recursively crawl
// pages starting with url, to a maximum of depth.
func Crawl(url string, depth int, fetcher Fetcher, ch chan CrawlReq, main bool) {
	// TODO: Fetch URLs in parallel.
	// TODO: Don't fetch the same URL twice.
	// This implementation doesn't do either:
	// fmt.Println("Crawl > ", url, depth)
	if !main {
		defer pcc.wg.Done()
	}
	if depth <= 0 {
		return
	}
	if Visited(url, true) {
		return
	}
	// fmt.Println("One > ", url)
	body, urls, err := fetcher.Fetch(url)

	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Printf("found: %s %q\n", url, body)

	for _, u := range urls {
		// fmt.Println("ch <- CR >", u)
		if !Visited(u, false) && depth > 1 {
			pcc.wg.Add(1)
			ch <- CrawlReq{ u, depth-1, false }
		}
	}
	if main {
		pcc.wg.Done()
		pcc.wg.Wait()
		close(ch)
	}
	return
}

func main() {
	pcc.wg.Add(1)
	ch := make(chan CrawlReq, 1)
	ch <- CrawlReq{"https://golang.org/", 4, true}
	for {
		cr, ok := <- ch
		fmt.Println("for > ", cr)
		if ok {
			go Crawl(cr.url, cr.depth, fetcher, ch, cr.main)
		} else {
			break
		}
	}
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
