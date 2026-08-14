# Regression test for NVL144 BMC SSD Reset log typo.
# Ensures the log message uses the correct signal name "BMC SSD Reset".
import pathlib
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parent.parent
SOURCE = REPO_ROOT / "src" / "platform" / "nvl144" / "nvl144_power_control.cpp"

def test_bmc_ssd_reset_log_typo():
    text = SOURCE.read_text()
    # The typo should not be present.
    assert "BMC SDD Reset" not in text, (
        f"Found typo 'BMC SDD Reset' in {SOURCE}; expected 'BMC SSD Reset'"
    )
    # The correct signal name should appear in the power-on log context.
    assert "de-asserting BMC SSD Reset" in text, (
        f"Expected correct log string 'de-asserting BMC SSD Reset' in {SOURCE}"
    )

if __name__ == "__main__":
    test_bmc_ssd_reset_log_typo()
