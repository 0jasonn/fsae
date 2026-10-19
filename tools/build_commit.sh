#!/bin/sh
# Rebuilds, checks the ROM still matches, and commits everything with the given message.
set -e
cd "$(dirname "$0")/.."
python tools/configure.py eur > /dev/null
# Compile first (linking may fail on new C++ names), give symbols.txt the mangled names, then build for real.
PATH=/c/tools/bin:$PATH ninja -k 0 > scratch/ninja.log 2>&1 || true
python tools/cxx_symbols.py | grep -v "^MISSING plain data_" || true
PATH=/c/tools/bin:$PATH ninja > scratch/ninja.log 2>&1 || { grep -iE "error|undefined|FAILED" scratch/ninja.log | head -20; exit 1; }
grep -q "fsae_eur.nds: OK" scratch/ninja.log || { echo "ROM does not match"; exit 1; }
python tools/stage_integrated.py
git -c user.name="Jason" -c user.email="matjas432@gmail.com" commit -q -m "$1

Co-Authored-By: Claude Opus 5.5 (1M context) <noreply@anthropic.com>"
echo "committed: $1"
