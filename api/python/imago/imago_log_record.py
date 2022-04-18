from array import array
from pathlib import Path


class ImagoLogRecord:
    def __init__(self, filename: Path, data: bytes) -> None:
        self.filename: Path = filename
        self.data: bytes = data
