package com.github.zukkari

import com.fasterxml.jackson.databind.ObjectMapper
import io.ktor.application.ApplicationCall
import io.ktor.cio.toByteArray
import io.ktor.http.ContentType
import io.ktor.http.HttpHeaders
import io.ktor.http.HttpStatusCode
import io.ktor.request.header
import io.ktor.response.respondText
import org.slf4j.Logger

open class Handler(protected val call: ApplicationCall, protected val log: Logger) {
    protected val mapper = ObjectMapper()

    open suspend fun handle() = Unit

    suspend fun respond(code: HttpStatusCode, message: String = "") {
        this.call.response.status(code)
        this.call.respondText { message }
    }
}

enum class Headers(val value: String) {
    AUTH("zauth"),
    FILE_NAME("zfile_name")
}

val apiKeys = listOf("7f00534ba1ec107e17131bc63e37d805")

class UploadHandler(call: ApplicationCall, log: Logger) : Handler(call, log) {

    override suspend fun handle() {
        val auth = call.request.header(Headers.AUTH.value)
        if (!authorized(auth ?: "")) {
            log.info("Not valid auth token: '$auth'")
            respond(HttpStatusCode.Unauthorized, "Missing API key")
            return
        }
        log.info("Valid token present: $auth")

        val mime = this.call.request.header(HttpHeaders.ContentType)
        log.info("Request MIME: $mime")
        if (mime == null) {
            respond(HttpStatusCode.UnsupportedMediaType, "Payload $ContentType not present")
            return
        }

        val attachmentName = this.call.request.header(Headers.FILE_NAME.value)
        log.info("Attachment name: $attachmentName")
        if (attachmentName == null) {
            respond(HttpStatusCode.PartialContent, "Content name not specified")
            return
        }

        if (this.call.request.receiveChannel().availableForRead < 0) {
            log.info("No content available for read")
            return
        }

        val content = this.call.request.receiveChannel().toByteArray()
        log.info("Received content of ${content.size} bytes")

        val handle = FileHandle(content, content.size, mime, attachmentName)
        Registry.register(handle).apply {
            handle.code = this
        }

        respond(HttpStatusCode.OK, mapper.writeValueAsString(handle))
    }

    private fun authorized(key: String) = key in apiKeys
}

class InfoHandler(call: ApplicationCall, log: Logger) : Handler(call, log) {
    override suspend fun handle() {
        TODO()
    }
}

class DownloadHandler(call: ApplicationCall, log: Logger) : Handler(call, log) {
    override suspend fun handle() {
        TODO()
    }
}