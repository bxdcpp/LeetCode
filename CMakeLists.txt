cmake_minimum_required (VERSION 2.8)
project(LeetCodeExample)

set(single_file_examples
	05longestPalindromes
	14longestCommonPrefix
	SlidingWindow
	BinaryTree
  )

foreach(example ${single_file_examples})
    add_executable(${example} "${example}.cpp")
endforeach(example)


