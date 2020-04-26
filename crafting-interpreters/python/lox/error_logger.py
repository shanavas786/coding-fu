#!/usr/bin/env python3

from .token_types import TokenType


class ErrorLogger:
    has_error = False
    has_runtime_error = False

    def error(line=None, token=None, message=""):
        if token:
            lexeme = (
                "end" if token.token_type == TokenType.EOF else "'" + token.lexeme + "'"
            )
            ErrorLogger.report(token.line, "at " + lexeme, message)
        else:
            ErrorLogger.report(line, "", message)

    def runtime_error(error):
        print(str(error), f"\n[line {error.token.line}]")
        ErrorLogger.has_runtime_error = True

    def report(line: int, where: str, message: str) -> None:
        print(f"[line {line}] Error {where}: {message}")
        ErrorLogger.has_error = True


class RuntimeException(Exception):
    def __init__(self, token, message):
        super().__init__(message)
        self.token = token
