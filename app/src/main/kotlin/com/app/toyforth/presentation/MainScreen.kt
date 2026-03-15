package com.app.toyforth.presentation

import android.graphics.RuntimeShader
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TextFieldDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableFloatStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.runtime.withFrameMillis
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.drawBehind
import androidx.compose.ui.focus.FocusRequester
import androidx.compose.ui.focus.focusRequester
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.ShaderBrush
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.SpanStyle
import androidx.compose.ui.text.buildAnnotatedString
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.text.withStyle
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel
import com.app.toyforth.presentation.MainViewModel.Companion.LINE_PREFIX

@Composable
fun MainScreen(
    pv: PaddingValues,
    mainViewModel: MainViewModel = viewModel()
) {
    var input by remember { mutableStateOf("") }
    val bgColor = Color.Black
    val primaryColor = Color.Green
    val lines by mainViewModel.lines.collectAsStateWithLifecycle()

    // field focus grabber //
    var refocus by remember { mutableStateOf(false) }
    val focusRequester = remember { FocusRequester() }
    LaunchedEffect(refocus) {
        if (refocus) {
            focusRequester.requestFocus()
            refocus = false
        }
    }

    // AGSL shader background //
    val context = LocalContext.current
    val shader = remember {
        val src = context.assets.open("shaders/orbit.agsl").bufferedReader().readText()
        RuntimeShader(src)
    }
    var time by remember { mutableFloatStateOf(0f) }
    LaunchedEffect(Unit) {
        val start = withFrameMillis { it }
        while (true) {
            withFrameMillis { frameTime ->
                time = (frameTime - start) / 1000f
            }
        }
    }

    Box(
        modifier = Modifier
            .fillMaxSize()
            .background(bgColor)
            .padding(pv)
            .drawBehind {
                shader.setFloatUniform("iResolution", size.width, size.height)
                shader.setFloatUniform("iTime", time)
                drawRect(brush = ShaderBrush(shader))
            },
        contentAlignment = Alignment.Center
    ) {
    LazyColumn(
        modifier = Modifier.fillMaxSize(),
        contentPadding = PaddingValues(horizontal = 10.dp, vertical = 10.dp)
    ) {
        items(lines.size) { i ->
            val line = lines[i]
            val text = if (line.byUser) {
                buildAnnotatedString {
                    withStyle(SpanStyle(color = primaryColor)) { append(LINE_PREFIX) }
                    withStyle(SpanStyle(color = Color.White)) { append(line.value) }
                }
            } else {
                buildAnnotatedString {
                    withStyle(SpanStyle(color = Color.White)) { append(line.value) }
                }
            }

            Text(
                modifier = Modifier.padding(vertical = 6.dp),
                text = text,
                maxLines = 1,
                overflow = TextOverflow.Ellipsis,
                style = MaterialTheme.typography.bodyMedium.copy(fontSize = 20.sp)
            )
        }

        item {
            Row(
                modifier = Modifier.padding(horizontal = 10.dp),
                verticalAlignment = Alignment.CenterVertically
            ) {
                Text(LINE_PREFIX, color = primaryColor, fontSize = 20.sp)
                TextField(
                    value = input,
                    onValueChange = { input = it },
                    modifier = Modifier
                        .weight(1f)
                        .focusRequester(focusRequester),
                    singleLine = true,
                    textStyle = MaterialTheme.typography.bodyMedium.copy(
                        color = Color.White,
                        fontSize = 20.sp
                    ),
                    colors = TextFieldDefaults.colors(
                        focusedIndicatorColor = Color.Transparent,
                        unfocusedIndicatorColor = Color.Transparent,
                        disabledIndicatorColor = Color.Transparent,
                        focusedContainerColor = Color.Transparent,
                        unfocusedContainerColor = Color.Transparent,
                        focusedTextColor = Color.White,
                        unfocusedTextColor = Color.White,
                        cursorColor = Color.White
                    ),
                    keyboardOptions = KeyboardOptions(imeAction = ImeAction.Done),
                    keyboardActions = KeyboardActions(
                        onDone = {
                            mainViewModel.runCommand(input)
                            input = ""
                            refocus = true
                        }
                    )
                )
            }
        }
    }
    } // Box

}
