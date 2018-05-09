import com.github.zukkari.DownloadHandler
import com.github.zukkari.InfoHandler
import com.github.zukkari.Registry
import com.github.zukkari.UploadHandler
import io.ktor.application.install
import io.ktor.application.log
import io.ktor.features.CORS
import io.ktor.http.HttpHeaders
import io.ktor.response.respondText
import io.ktor.routing.get
import io.ktor.routing.post
import io.ktor.routing.routing
import io.ktor.server.engine.embeddedServer
import io.ktor.server.tomcat.Tomcat
import org.slf4j.Logger
import java.io.File
import java.nio.file.Files
import java.time.Duration
import java.util.Properties
import kotlin.system.measureTimeMillis

enum class Keys(val value: String) {
    PORT("server.port"),
    FILE_DIR("server.tmp.dir"),
    ADJECTIVES("server.keys.adj"),
    NOUNS("server.keys.noun")
}

fun main(args: Array<String>) {
    val props = Properties().apply {
        this.load(Keys::class.java.getResourceAsStream("zshare.properties"))
    }
    val port: Int = (props[Keys.PORT.value] as String).toInt()
    Registry.initialize(props)

    embeddedServer(Tomcat, port) {
        log.info("Started server on port $port")

        runStartUp(log, props)

        install(CORS) {
            header(HttpHeaders.Origin)
            anyHost()
            maxAge = Duration.ofDays(1)
        }

        routing {
            get("/info", {
                log.info("Serving endpoint 'info'")
                this.context.respondText { "Future endpoint implementation" }
                InfoHandler(this.context).handle()
            })

            post("/files", {
                log.info("Handling file upload at 'files'")
                UploadHandler(this.context).handle()
            })

            get("/files", {
                log.info("Setting up a download for file at 'files'")
                this.context.respondText { "Future endpoint implementation" }
                DownloadHandler(this.context).handle()
            })
        }
    }.start(wait = true)
}

fun runStartUp(log: Logger, props: Properties) {
    measureTimeMillis {
        val dir = props[Keys.FILE_DIR.value] as String
        log.info("Setting up temp directory at $dir")

        File(dir).run {
            if (this.exists() && this.isDirectory) {
                log.info("${this.absolutePath} is an already existing directory, skipping set up")
                return@run
            }

            Files.createDirectory(this.toPath()).apply {
                log.info("Created temp directory at ${this.toAbsolutePath()}")
            }
        }
    }.apply {
        log.info("Finished setup in $this ms")
    }
}
