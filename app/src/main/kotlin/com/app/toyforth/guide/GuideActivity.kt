package com.app.toyforth.guide

import android.graphics.Color
import android.os.Bundle
import android.widget.TextView
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.compose.ui.viewinterop.AndroidView
import io.noties.markwon.Markwon

// Markdown guide
class GuideActivity : ComponentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()

        setContent {
            MaterialTheme {
                Scaffold(
                    modifier = Modifier.fillMaxSize(),
                ) { innerPadding ->
                    Column(
                        modifier = Modifier
                            .fillMaxSize()
                            .background(androidx.compose.ui.graphics.Color.Black)
                            .padding(innerPadding).padding(horizontal = 16.dp),
                    ) {
                        AndroidView(
                            modifier = Modifier.padding(top = 16.dp),
                            factory = { ctx ->
                                TextView(ctx).apply {
                                    setTextColor(Color.WHITE)
                                    val markwon = Markwon.builder(ctx).build()

                                    val markdown = assets.open("README.md").bufferedReader()
                                        .use { it.readText() }

                                    markwon.setMarkdown(this, markdown)
                                }
                            }
                        )
                    }

                }
            }
        }
    }
}