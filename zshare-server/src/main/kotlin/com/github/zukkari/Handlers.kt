package com.github.zukkari

import io.ktor.application.ApplicationCall

interface Handler {
    fun handle()
}

class UploadHandler(val call: ApplicationCall) : Handler {
    override fun handle() {
        TODO()
    }
}

class InfoHandler(val call: ApplicationCall) : Handler {
    override fun handle() {
        TODO()
    }
}

class DownloadHandler(val call: ApplicationCall) : Handler {
    override fun handle() {
        TODO()
    }
}