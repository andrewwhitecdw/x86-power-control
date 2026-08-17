#!/usr/bin/env bash
set -euo pipefail

file=src/bmc/bmc_state_manager.cpp
grep -q 'std::this_thread::sleep_for(std::chrono::seconds(2));' "$file"
! grep -q 'usleep(' "$file"
