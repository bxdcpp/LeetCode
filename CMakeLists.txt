cmake_minimum_required (VERSION 2.8)
project(LeetCodeExample)

set(single_file_examples
	04longestPalindromes
	14longestCommonPrefix
	SlidingWindow
  )

foreach(example ${single_file_examples})
    add_executable(${example} "${example}.cpp")
endforeach(example)


