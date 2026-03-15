package com.app.toyforth

import android.content.Intent
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.WindowInsets
import androidx.compose.foundation.layout.asPaddingValues
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.systemBars
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Info
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.core.splashscreen.SplashScreen.Companion.installSplashScreen
import com.app.toyforth.guide.GuideActivity
import com.app.toyforth.presentation.MainScreen

class MainActivity : ComponentActivity() {

    init {
        System.loadLibrary("toyforth")
    }

    companion object {
        @JvmStatic
        external fun runCommand(command: String): String
    }

    @OptIn(ExperimentalMaterial3Api::class)
    override fun onCreate(savedInstanceState: Bundle?) {
        installSplashScreen()
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()

        setContent {
            MaterialTheme {
                Scaffold(modifier = Modifier.fillMaxSize(), topBar = {

                    // Safe content
                    Box(
                        modifier = Modifier
                            .fillMaxWidth()
                            .padding(WindowInsets.systemBars.asPaddingValues()),
                        contentAlignment = Alignment.TopEnd
                    ) {
                        IconButton(onClick = {
                            startActivity(Intent(this@MainActivity, GuideActivity::class.java))
                        }) {
                            Icon(
                                imageVector = Icons.Default.Info,
                                contentDescription = "Guide",
                                tint = Color.White
                            )
                        }
                    }
                }) { innerPadding ->
                    MainScreen(innerPadding)
                }
            }
        }
    }

}