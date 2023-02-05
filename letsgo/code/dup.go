package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func countLines(f *os.File, counter map[string]int) {
	input := bufio.NewScanner(f)

	for input.Scan() {
		counter[input.Text()]++
	}
}

func dup1() {
	counter := make(map[string]int)
	input := bufio.NewScanner(os.Stdin)

	for input.Scan() {
		counter[input.Text()]++
	}

	for line, n := range counter {
		if n > 1 {
			fmt.Printf("%d\t%s\n", n, line)
		}
	}
}

func dup2() {
	counter := make(map[string]int)
	files := os.Args[1:]

	if len(files) == 0 {
		countLines(os.Stdin, counter)
	} else {
		for _, file := range files {
			f, err := os.Open(file)
			if err != nil {
				fmt.Fprintf(os.Stderr, "dump2: %v\n", err)
				continue
			}
			countLines(f, counter)
			f.Close()
		}
	}

	for line, n := range counter {
		if n > 1 {
			fmt.Printf("%d\t%s\n", n, line)
		}
	}
}

func dup3() {
	counter := make(map[string]int)

	for _, filename := range os.Args[1:] {
		data, err := os.ReadFile(filename)
		if err != nil {
			fmt.Fprintf(os.Stderr, "dump3: %v\n", err)
			continue
		}

		for _, line := range strings.Split(string(data), "\n") {
			counter[line]++
		}
	}

	for line, n := range counter {
		if n > 1 {
			fmt.Printf("%d\t%s\n", n, line)
		}
	}
}
