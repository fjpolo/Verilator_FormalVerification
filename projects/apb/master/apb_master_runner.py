# apb_master_runner.py

import os
from pathlib import Path

from cocotb.runner import get_runner


def test_apb_master_runner():
    sim = os.getenv("SIM", "icarus")

    proj_path = Path(__file__).resolve().parent

    sources = [proj_path / "apb_master.v"]

    runner = get_runner(sim)
    runner.build(
        sources=sources,
        hdl_toplevel="apb_master",
    )

    runner.test(hdl_toplevel="apb_master", test_module="apb_master_tb,")


if __name__ == "__main__":
    test_apb_master_runner()