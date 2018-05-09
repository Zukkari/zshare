package com.github.zukkari

import Keys
import java.io.BufferedReader
import java.io.File
import java.io.FileReader
import java.util.Properties
import java.util.Random
import java.util.concurrent.ConcurrentHashMap

data class FileHandle(
        val file: File,
        val contentSize: Int,
        val mime: String,
        val key: String,
        val checksum: String)

object Registry {
    private val fileMap = ConcurrentHashMap<String, FileHandle>()

    private lateinit var adjectives: List<String>
    private lateinit var nouns: List<String>

    private val random: Random = Random()

    fun register(handle: FileHandle): String {
        return generateKey().apply {
            fileMap[this] = handle
        }
    }

    fun extract(key: String) = fileMap[key]

    fun initialize(props: Properties) {
        (props[Keys.ADJECTIVES.value] as String).apply {
            BufferedReader(FileReader(File(Keys::class.java.getResource(this).toURI()))).use {
                adjectives = it.readLines()
            }
        }

        (props[Keys.NOUNS.value] as String).apply {
            BufferedReader(FileReader(File(Keys::class.java.getResource(this).toURI()))).use {
                nouns = it.readLines()
            }
        }
    }

    private tailrec fun generateKey(): String {
        val num = random.nextInt(10)
        val adj = adjectives[random.nextInt(adjectives.size - 1)]
        val noun = nouns[random.nextInt(nouns.size - 1)]

        val key = "$num-$adj-$noun"
        return if (key !in fileMap) {
            key
        } else {
            generateKey()
        }
    }
}