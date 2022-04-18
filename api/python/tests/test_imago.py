import unittest
from pathlib import Path

from imago import Imago, ImagoException
from imago.imago_filters import ImagoFilter
from PIL import Image
from tests import CAFFEINE_JPG, OUTPUT_DIR


class ImagoTest(unittest.TestCase):
    def setUp(self) -> None:
        self.imago = Imago()

    def test_imago_version(self) -> None:
        assert self.imago.version

    def test_load_pillow_save_pillow(self) -> None:
        with Image.open(str(CAFFEINE_JPG)) as image:
            original = image.convert("L")
            self.imago.load_image_from_pillow(original)
        result = self.imago.image
        original_path = (
            OUTPUT_DIR / "test_load_pillow_save_pillow_original.jpg"
        )
        original.save(original_path)
        result_path = OUTPUT_DIR / "test_load_pillow_save_pillow_result.jpg"
        result.save(result_path)
        assert original_path.stat().st_size == result_path.stat().st_size

    def test_load_pillow_save_file(self) -> None:
        with Image.open(str(CAFFEINE_JPG)) as image:
            self.imago.load_image_from_pillow(image)
        self.imago.save_image_to_file(
            OUTPUT_DIR / "test_load_pillow_save_file.jpg"
        )

    def test_load_file_save_file(self) -> None:
        self.imago.load_image_from_file(CAFFEINE_JPG)
        self.imago.save_image_to_file(
            OUTPUT_DIR / "test_load_file_save_file.jpg"
        )

    def test_load_buffer_save_file(self) -> None:
        with CAFFEINE_JPG.open("rb") as f:
            data = f.read()
        self.imago.load_image_from_buffer(data)
        self.imago.save_image_to_file(
            OUTPUT_DIR / "test_load_buffer_save_file.jpg"
        )

    def test_filter_image(self) -> None:
        self.imago.load_image_from_file(CAFFEINE_JPG)
        self.imago.filter_image(ImagoFilter.BASIC)
        self.imago.filter_image(ImagoFilter.BASIC_S)
        self.imago.filter_image(ImagoFilter.BINARIZED)
        self.imago.filter_image(ImagoFilter.RETINEX)
        self.imago.save_image_to_file(OUTPUT_DIR / "test_filter_image.jpg")

    def test_get_log_records(self) -> None:
        self.imago.load_image_from_file(CAFFEINE_JPG)
        self.imago.filter_image(ImagoFilter.BASIC)
        for log_record in self.imago.log_records:
            print(log_record.filename)

    def test_all_to_file(self) -> None:
        self.imago.load_image_from_file(CAFFEINE_JPG)
        self.imago.filter_image(ImagoFilter.BASIC)
        warnings = (
            self.imago.recognize()
        )  # TODO: check warnings if there count should be 0 (currently 2)
        output_file = OUTPUT_DIR / "caffeine.mol"
        self.imago.save_molecule_to_file(output_file)
        assert output_file.stat().st_size
        for log_record in self.imago.log_records:
            print(log_record.filename)

    def test_all_to_str(self) -> None:
        self.imago.load_image_from_file(CAFFEINE_JPG)
        self.imago.filter_image(ImagoFilter.BASIC)
        warnings = (
            self.imago.recognize()
        )  # TODO: find out why we have 2 warnings, but no log records, is it ok?
        result = self.imago.molecule
        assert result
        for log_record in self.imago.log_records:
            print(log_record.filename)

    def test_all_to_str_set_filter(self) -> None:
        self.imago.load_image_from_file(CAFFEINE_JPG)
        self.imago.filter_image(ImagoFilter.BASIC)
        self.imago.filter_image(ImagoFilter.BINARIZED)
        warnings = (
            self.imago.recognize()
        )  # TODO: find out why we have 2 warnings, but no log records, is it ok?
        result = self.imago.molecule
        assert result
        for log_record in self.imago.log_records:
            print(log_record.filename)

    def test_ink_percentage(self) -> None:
        self.imago.load_image_from_file(CAFFEINE_JPG)
        orignal_ink_percentage = self.imago.image_ink_percentage
        assert 0.03 < orignal_ink_percentage < 0.04
        self.imago.filter_image(ImagoFilter.BASIC)
        filtered_ink_percentage = self.imago.image_ink_percentage
        assert 0.03 < orignal_ink_percentage < 0.04
        assert orignal_ink_percentage != filtered_ink_percentage

    def test_configs(self):
        try:
            assert self.imago.configs is not None
        except ImagoException as e:
            self.fail(e)

    def test_set_config_invalid(self):
        with self.assertRaises(ImagoException):
            self.imago.set_config(Path("/i/dont/exist.txt"))
