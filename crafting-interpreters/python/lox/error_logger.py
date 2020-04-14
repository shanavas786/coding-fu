#!/usr/bin/env python3


class ErrorLogger:
    def error(line, message):
        ErrorLogger.report(line, "", message)

    def report(line: int, where: str, message: str) -> None:
        print(f"[line {line}] Error {where}: {message}")
