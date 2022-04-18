import platform
import threading
from ctypes import (
    CDLL,
    POINTER,
    byref,
    c_byte,
    c_char_p,
    c_double,
    c_int,
    c_ubyte,
    c_ulonglong,
    cast,
    pointer,
)
from pathlib import Path
from typing import AnyStr, Generic, List, Optional, Tuple, TypeVar

from imago.imago_exception import ImagoException
from imago.imago_filters import ImagoFilter
from imago.imago_log_record import ImagoLogRecord
from PIL import Image

T = TypeVar("T")


class Imago:
    _lib: Optional[CDLL] = None
    _lib_indigo: Optional[CDLL] = None
    _lib_lock: threading.Lock = threading.Lock()

    @staticmethod
    def _get_system_name() -> str:
        return platform.uname().system.lower()

    @staticmethod
    def _get_arch_name() -> str:
        replacement_dict = {"amd64": "x86_64"}
        raw_arch = platform.uname().machine.lower()
        return replacement_dict.get(raw_arch, raw_arch)

    @staticmethod
    def _get_shared_library_name(basename: str) -> str:
        system = Imago._get_system_name()
        if system == "windows":
            library_prefix = ""
            library_suffix = ".dll"
        elif system == "linux":
            library_prefix = "lib"
            library_suffix = ".so"
        elif system == "darwin":
            library_prefix = "lib"
            library_suffix = ".dylib"
        else:
            raise RuntimeError(f"Unsupported OS: {system}")
        return f"{library_prefix}{basename}{library_suffix}"

    @staticmethod
    def _get_path_to_native_library(lib_name: str) -> Path:
        package_path = Path(__file__).parent
        system = Imago._get_system_name()
        arch = Imago._get_arch_name()
        folder = package_path / "lib" / f"{system}-{arch}"
        return folder / Imago._get_shared_library_name(lib_name)

    @staticmethod
    def _init_native_lib() -> None:
        with Imago._lib_lock:
            # Imago._lib_indigo = CDLL(str(Imago._get_path_to_native_library("indigo")))
            Imago._lib = CDLL(str(Imago._get_path_to_native_library("imago")))
            # imagoAllocSessionId
            Imago._lib.imagoAllocSessionId.restype = c_ulonglong
            Imago._lib.imagoAllocSessionId.argtypes = None
            # imagoClearLog
            Imago._lib.imagoClearLog.restype = c_int
            Imago._lib.imagoClearLog.argtypes = None
            # imagoFilterImage
            Imago._lib.imagoFilterImage.restype = c_int
            Imago._lib.imagoFilterImage.argtypes = []
            # imagoGetConfigsList
            Imago._lib.imagoGetConfigsList.restype = c_char_p
            Imago._lib.imagoGetConfigsList.argtypes = []
            # imagoGetInkPercentage
            Imago._lib.imagoGetInkPercentage.restype = c_int
            Imago._lib.imagoGetInkPercentage.argtypes = [POINTER(c_double)]
            # imagoGetLastError
            Imago._lib.imagoGetLastError.restype = c_char_p
            Imago._lib.imagoGetLastError.argtypes = None
            # imagoGetLogCount
            Imago._lib.imagoGetLogCount.restype = c_int
            Imago._lib.imagoGetLogCount.argtypes = [POINTER(c_int)]
            # imagoGetLogRecord
            Imago._lib.imagoGetLogRecord.restype = c_int
            Imago._lib.imagoGetLogRecord.argtypes = [
                c_int,
                POINTER(POINTER(c_byte)),
                POINTER(c_int),
                POINTER(POINTER(c_byte)),
            ]
            # imagoGetPrefilteredImage
            Imago._lib.imagoGetPrefilteredImage.restype = c_int
            Imago._lib.imagoGetPrefilteredImage.argtypes = [
                POINTER(POINTER(c_ubyte)),
                POINTER(c_int),
                POINTER(c_int),
            ]
            # imagoGetPrefilteredImageSize
            Imago._lib.imagoGetPrefilteredImageSize.restype = c_int
            Imago._lib.imagoGetPrefilteredImageSize.argtypes = [
                POINTER(c_int),
                POINTER(c_int),
            ]
            # imagoGetMol
            Imago._lib.imagoGetMol.restype = c_char_p
            Imago._lib.imagoGetMol.argtypes = None
            # imagoGetVersion
            Imago._lib.imagoGetVersion.restype = c_char_p
            Imago._lib.imagoGetVersion.argtypes = None
            # imagoLoadGreyscaleRawImage
            Imago._lib.imagoLoadGreyscaleRawImage.restype = c_int
            Imago._lib.imagoLoadGreyscaleRawImage.argtypes = [
                POINTER(c_byte),
                c_int,
                c_int,
            ]
            # imagoLoadImageFromBuffer
            Imago._lib.imagoLoadImageFromBuffer.restype = c_int
            Imago._lib.imagoLoadImageFromBuffer.argtypes = [
                POINTER(c_byte),
                c_int,
            ]
            # imagoLoadImageFromFile
            Imago._lib.imagoLoadImageFromFile.restype = c_int
            Imago._lib.imagoLoadImageFromFile.argtypes = [c_char_p]
            # imagoRecognize
            Imago._lib.imagoRecognize.restype = c_int
            Imago._lib.imagoRecognize.argtypes = [POINTER(c_int)]
            # imagoReleaseSessionId
            Imago._lib.imagoReleaseSessionId.restype = None
            Imago._lib.imagoReleaseSessionId.argtypes = [c_ulonglong]
            # imagoSaveImageToFile
            Imago._lib.imagoSaveImageToFile.restype = c_int
            Imago._lib.imagoSaveImageToFile.argtypes = [c_char_p]
            # imagoSaveMolToFile
            Imago._lib.imagoSaveMolToBuffer.restype = c_int
            Imago._lib.imagoSaveMolToBuffer.argtypes = [c_char_p]
            # imagoSetConfig
            Imago._lib.imagoSetConfig.restype = c_int
            Imago._lib.imagoSetConfig.argtypes = [c_char_p]
            # imagoSetFilter
            Imago._lib.imagoSetFilter.restype = c_int
            Imago._lib.imagoSetFilter.argtypes = [c_char_p]
            # imagoSetLogging
            Imago._lib.imagoSetLogging.restype = c_int
            Imago._lib.imagoSetLogging.argtypes = [c_int]
            # imagoSetSessionId
            Imago._lib.imagoSetSessionId.restype = None
            Imago._lib.imagoSetSessionId.argtypes = [c_ulonglong]
            # Archive
            # TODO: check if we need any of this
            # # imagoGetSessionSpecificData
            # Imago._lib.imagoGetSessionSpecificData.restype = c_int
            # Imago._lib.imagoGetSessionSpecificData.argtypes = [POINTER(POINTER(c_byte))]
            # # imagoSaveMolToBuffer
            # Imago._lib.imagoSaveMolToBuffer.restype = c_int
            # Imago._lib.imagoSaveMolToBuffer.argtypes = [POINTER(c_char_p), POINTER(c_int)]
            # # imagoSetSessionSpecificData
            # Imago._lib.imagoSetSessionSpecificData.restype = c_int
            # Imago._lib.imagoSetSessionSpecificData.argtypes = [POINTER(c_byte)]

    def _set_session_id(self) -> None:
        Imago._lib.imagoSetSessionId(self._session_id)

    @staticmethod
    def _check_result_ptr(result: Generic[T]) -> T:
        if not result:
            raise ImagoException(Imago._lib.imagoGetLastError())
        return result

    @staticmethod
    def _check_result_str(result: AnyStr) -> AnyStr:
        return Imago._check_result_ptr(result)

    @staticmethod
    def _check_result(result: int) -> int:
        if result == 0:
            raise ImagoException(Imago._lib.imagoGetLastError())
        return result

    # Public API

    def __init__(self) -> None:
        if not Imago._lib:
            Imago._init_native_lib()
        self._session_id = Imago._lib.imagoAllocSessionId()

    def __del__(self) -> None:
        Imago._lib.imagoReleaseSessionId(self._session_id)

    def load_image_from_pillow(self, image: Image) -> None:
        """Load raw grayscale image from Pillow Image instance"""
        image = image.convert("L")
        width = c_int(image.width)
        height = c_int(image.height)
        data = image.tobytes("raw")
        image_size = image.width * image.height
        buf = (c_byte * image_size)()
        for i in range(image_size):
            buf[i] = data[i]
        self._set_session_id()
        Imago._check_result(
            Imago._lib.imagoLoadGreyscaleRawImage(buf, width, height)
        )

    def load_image_from_buffer(self, buffer: bytes) -> None:
        """Load image from buffer with given size"""
        buf = (c_byte * len(buffer))()
        for i in range(len(buffer)):
            buf[i] = buffer[i]
        self._set_session_id()
        Imago._check_result(
            Imago._lib.imagoLoadImageFromBuffer(buf, len(buffer))
        )

    def load_image_from_file(self, filename: Path) -> None:
        """Load image from file"""
        self._set_session_id()
        Imago._check_result(
            Imago._lib.imagoLoadImageFromFile(str(filename).encode())
        )

    def set_config(self, filename: Path) -> None:
        """Set config file"""
        self._set_session_id()
        Imago._check_result(Imago._lib.imagoSetConfig(str(filename).encode()))

    @property
    def configs(self) -> List[str]:
        """Get the list of available predefined configuration sets"""
        self._set_session_id()
        result = Imago._lib.imagoGetConfigsList()
        if not result:
            return []
        return result.decode().split(",")

    def filter_image(self, imago_filter: ImagoFilter) -> None:
        """Set image filter according to parameter and process filtering. Should be performed before recognize()"""
        self._set_session_id()
        Imago._check_result(
            Imago._lib.imagoSetFilter(imago_filter.value.encode())
        )
        Imago._check_result(Imago._lib.imagoFilterImage())

    def recognize(self) -> int:
        """
        Main recognition routine. Image must be loaded & filtered previously
        Returns count of recognition warnings in warningsCountDataOut value (if specified)
        """
        warnings_count = c_int()
        self._set_session_id()
        Imago._check_result(Imago._lib.imagoRecognize(byref(warnings_count)))
        return warnings_count.value

    @property
    def image(self) -> Image:
        """Returns filtered image"""
        width = c_int()
        height = c_int()
        buffer = POINTER(c_ubyte)()
        self._set_session_id()
        Imago._check_result(
            Imago._lib.imagoGetPrefilteredImage(
                pointer(buffer), byref(width), byref(height)
            )
        )
        size = width.value * height.value
        data = memoryview(cast(buffer, POINTER(c_ubyte * size))[0]).tobytes()
        return Image.frombytes(
            mode="L", size=(width.value, height.value), data=bytes(data)
        )

    @property
    def image_size(self) -> Tuple[int, int]:
        """Returns filtered image dimensions (width and height)"""
        width = c_int()
        height = c_int()
        self._set_session_id()
        Imago._check_result(
            Imago._lib.imagoGetPrefilteredImageSize(
                byref(width), byref(height)
            )
        )
        return width.value, height.value

    @property
    def image_ink_percentage(self) -> float:
        """Returns image ink percentage (0.0..1.0)"""
        result = c_double()
        self._set_session_id()
        Imago._check_result(Imago._lib.imagoGetInkPercentage(byref(result)))
        return result.value

    def save_image_to_file(self, filename: Path) -> None:
        """Save image to file"""
        self._set_session_id()
        Imago._check_result(
            Imago._lib.imagoSaveImageToFile(str(filename).encode())
        )

    @property
    def molecule(self) -> str:
        """Return recognized molecule in Molfile format as a string"""
        self._set_session_id()
        return Imago._check_result_str(Imago._lib.imagoGetMol()).decode()

    def save_molecule_to_file(self, filename: Path) -> None:
        """Save recognized molecule as a molfile to specified file path"""
        self._set_session_id()
        Imago._check_result(
            Imago._lib.imagoSaveMolToFile(str(filename).encode())
        )

    @property
    def version(self) -> str:
        """Get the version of Imago"""
        self._set_session_id()
        return Imago._check_result_str(Imago._lib.imagoGetVersion()).decode()

    @property
    def log_count(self) -> int:
        """Returns count of files contained in log vfs"""
        result = c_int()
        self._set_session_id()
        Imago._check_result(Imago._lib.imagoGetLogCount(byref(result)))
        return result.value

    def get_log_record(self, index: int) -> ImagoLogRecord:
        """Returns a log record for given index"""
        name = c_char_p()
        buffer = POINTER(c_byte)()
        length = c_int()
        self._set_session_id()
        Imago._check_result(
            Imago._lib.imagoGetLogRecord(
                index, pointer(name), pointer(buffer), byref(length)
            )
        )
        data_result = memoryview(
            cast(buffer, POINTER(c_ubyte * length.value))[0]
        ).tobytes()
        name_result = str(name.value)
        return ImagoLogRecord(Path(name_result), data_result)

    def clear_log(self) -> None:
        """Clears all current vfs log content"""
        self._set_session_id()
        Imago._check_result(Imago._lib.imagoClearLog())

    @property
    def log_records(self) -> List[ImagoLogRecord]:
        """Returns all log records"""
        result = []
        for i in range(self.log_count):
            result.append(self.get_log_record(i))
        return result
