#!/usr/bin/env python3
from mupq import mupq
from interface import parse_arguments, get_platform


BENCH_TARGETS = [
        '--stack', '--speed', '--hashing', '--size', '--speed', '--subspeed', '--all'
        ]

import functools as ft
class SubSpeedBenchmark(mupq.StackBenchmark):
    test_type = 'speed_sub'

    # Filter function to filter debug from bench
    def filter_debug(self,log):
        #Constant for DEBUG parging
        cst_debug = "[DEBUG]"
        lines = log.split("\n")

        lines_bench = []
        lines_debug = []

        for l in lines:
            if l.startswith(cst_debug):
                lines_debug += [l]
            else:
                lines_bench += [l]
        # Reformat as text
        text_bench = ft.reduce(lambda a,b:a+'\n'+b, lines_bench)
        text_debug = ft.reduce(lambda a,b:a+'\n'+b, lines_bench)
        
        return text_bench, text_debug

    def run_test(self,implementation):
        self.log.info("Benchmarking %s",implementation)
        output = supepr(mupq.StackBenchmark, self).run_test(implementation)
        # Filter text
        txt_bench, txt_debug = self.filter_debug(output)
        print("####### START DEBUG LOG #######")
        print(txt_debug)
        print("####### SEND DEBUG LOG #######")
        self.write_result(implementation, txt_bench)


if __name__ == "__main__":
    args, rest = parse_arguments()
    platform, settings = get_platform(args)
    with platform:
        schemes = [s for s in rest if not s.startswith('--')]
        if not set(rest).intersection(set(BENCH_TARGETS)):
            print("No benchmark target selected.")
            print(f"Choose some of {', '.join(BENCH_TARGETS)}.")
        else:
            if "--stack" in rest or '--all' in rest:
                test = mupq.StackBenchmark(settings, platform)
                test.test_all(schemes)
            if "--speed" in rest or '--all' in rest:
                test = mupq.SpeedBenchmark(settings, platform)
                test.test_all(schemes)
            if "--hashing" in rest or '--all' in rest:
                test = mupq.HashingBenchmark(settings, platform)
                test.test_all(schemes)
            if "--size" in rest or '--all' in rest:
                test = mupq.SizeBenchmark(settings, platform)
                test.test_all(schemes)
            if "--subspeed" in rest or '--all' in rest:
                test = SubSpeedBenchmark(settings, platform)
                test.test_all(schemes)
