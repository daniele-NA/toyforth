package com.app.toyforth

import android.content.Intent
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Info
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.sp
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

                    TopAppBar(
                        title = {
                            Text(
                                "Toy Forth",
                                style = TextStyle(fontWeight = FontWeight.Bold, fontSize = 25.sp)
                            )
                        },
                        colors = TopAppBarDefaults.topAppBarColors(containerColor = MaterialTheme.colorScheme.primaryContainer),
                        actions = {
                            IconButton(onClick = {
                                startActivity(Intent(this@MainActivity, GuideActivity::class.java))
                            }) {
                                Icon(
                                    imageVector = Icons.Default.Info,
                                    contentDescription = "Guide",
                                    tint = MaterialTheme.colorScheme.onPrimaryContainer
                                )
                            }
                        }
                    )
                }) { innerPadding ->
                    MainScreen(innerPadding)
                }
            }
        }
    }

}