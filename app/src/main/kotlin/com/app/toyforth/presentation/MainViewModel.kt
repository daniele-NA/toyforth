package com.app.toyforth.presentation

import androidx.lifecycle.ViewModel
import com.app.toyforth.MainActivity
import com.app.toyforth.core.LOG
import com.app.toyforth.domain.Line
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update

class MainViewModel: ViewModel() {

    companion object{
         const val LINE_PREFIX ="shell > "
    }

    private val _lines= MutableStateFlow<List<Line>>(emptyList())
    val lines=_lines.asStateFlow()

    init {
        _lines.update {
            listOf(
                Line(value = "status --verbose", byUser = true),
                Line(value = "connect localhost:8080", byUser = true),
                Line(value = "fetch --limit 10", byUser = false),
                Line(value = "run task_dummy --force", byUser = true),
                Line(value = "exit", byUser = true)
            )
        }
    }

    fun runCommand(rawInput:String){
        val input = rawInput.removePrefix(LINE_PREFIX)
        _lines.update {
            _lines.value.plus(Line(value = input, byUser = true))
        }
        LOG("Running => $input")

        // Update the list with interpreter result
        try {
            val result = MainActivity.runCommand(input)

            _lines.update {
                _lines.value.plus(Line(value = result, byUser = false))
            }

        }catch (e: Exception){
            LOG("Eccezione runCommand ${e.message}")
        }
    }




}