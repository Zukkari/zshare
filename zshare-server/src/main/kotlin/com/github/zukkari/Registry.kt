package com.github.zukkari

import Keys
import com.fasterxml.jackson.annotation.JsonIgnore
import com.fasterxml.jackson.annotation.JsonProperty
import java.io.BufferedReader
import java.io.File
import java.io.FileReader
import java.util.Arrays
import java.util.Properties
import java.util.Random
import java.util.concurrent.ConcurrentHashMap


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

data class FileHandle(
        @field:JsonIgnore val content: ByteArray,
        @field:JsonProperty(value = "content_size") val contentSize: Int,
        @field:JsonProperty(value = "content-type") val mime: String,
        @field:JsonProperty(value = "file_name") val fileName: String) {

    @JsonProperty(value = "access-code")
    lateinit var code: String

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as FileHandle

        if (!Arrays.equals(content, other.content)) return false
        if (contentSize != other.contentSize) return false
        if (mime != other.mime) return false

        return true
    }

    override fun hashCode(): Int {
        var result = Arrays.hashCode(content)
        result = 31 * result + contentSize
        result = 31 * result + mime.hashCode()
        return result
    }
}