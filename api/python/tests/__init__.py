from datetime import datetime
from pathlib import Path

TESTS_DIR = Path(__file__).parent
DATA_DIR = TESTS_DIR / "data"
CAFFEINE_JPG = DATA_DIR / "caffeine.jpg"
OUTPUT_DIR = TESTS_DIR / "output" / datetime.now().strftime("%y%m%d_%H%M%S")

OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
