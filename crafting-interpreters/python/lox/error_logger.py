#!/usr/bin/env python3

from .token_types import TokenType


class ErrorLogger:
    def error(line=None, token=None, message=""):
        if token:
            lexeme = (
                "end" if token.token_type == TokenType.EOF else "'" + token.lexeme + "'"
            )
            ErrorLogger.report(token.line, "at " + lexeme, message)
        else:
            ErrorLogger.report(line, "", message)

    def report(line: int, where: str, message: str) -> None:
        print(f"[line {line}] Error {where}: {message}")
