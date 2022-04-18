import enum


@enum.unique
class ImagoFilter(enum.Enum):
    BASIC = "prefilter_basic"
    BASIC_S = "prefilter_basic_s"
    BINARIZED = "prefilter_binarized"
    RETINEX = "prefilter_retinex"
