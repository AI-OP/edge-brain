# Copyright 2021 The Edge Brain Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

licenses(["notice"])  # Apache 2.0

alias(
    name = "image_classifier_rpi",
    actual = "@image_classifier//image_classifier/apps/raspberry_pi:image_classifier",
)

alias(
    name = "benchmark_rpi",
    actual = "@image_classifier//image_classifier/apps/raspberry_pi:image_classifier_benchmark",
)

alias(
    name = "benchmark_coral",
    actual = "@image_classifier//image_classifier/apps/coral:image_classifier_benchmark_edgetpu",
)

alias(
    name = "benchmark_coral_cpu_only",
    actual = "@image_classifier//image_classifier/apps/coral:image_classifier_benchmark_cpu_only",
)
