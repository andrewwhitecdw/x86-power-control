#!/bin/bash
set -euo pipefail

SCRIPT="${1:-src/bmc/powerctrl.sh}"

if [ ! -f "$SCRIPT" ]; then
    echo "Script not found: $SCRIPT" >&2
    exit 1
fi

# The LOG_PID assignment in power_on should not have trailing whitespace.
trailing_lines=$(grep -nE '^    LOG_PID=\$![[:space:]]+$' "$SCRIPT" || true)
if [ -n "$trailing_lines" ]; then
    echo "Found LOG_PID assignment with trailing whitespace:" >&2
    printf '%s\n' "$trailing_lines" >&2
    exit 1
fi

# Ensure the expected LOG_PID assignment is present without trailing whitespace.
grep -qE '^    LOG_PID=\$!$' "$SCRIPT" || {
    echo "Expected LOG_PID assignment not found." >&2
    exit 1
}

echo "OK: no trailing whitespace after LOG_PID assignment"
