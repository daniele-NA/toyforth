package com.app.toyforth.presentation

import androidx.lifecycle.ViewModel
import com.app.toyforth.MainActivity
import com.app.toyforth.core.LOG
import com.app.toyforth.domain.Line
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update

class MainViewModel : ViewModel() {

    companion object {
        const val LINE_PREFIX = "user@android:~$ "
        const val CLEAR_COMMAND = "clear"
    }

    private val _lines = MutableStateFlow<List<Line>>(emptyList())
    val lines = _lines.asStateFlow()

    // Controllo sui caratteri ed esecuzione comando
    fun runCommand(rawInput: String) {

        // clean command
        if (rawInput.removePrefix(LINE_PREFIX) == CLEAR_COMMAND) {
            _lines.update { emptyList() };return;
        }
        if (rawInput.isEmpty() || !Regex("^[0-9+\\-*/% ]+$").matches(rawInput)) return


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

        } catch (e: Exception) {
            LOG("Eccezione runCommand ${e.message}")
        }
    }


}