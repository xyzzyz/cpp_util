cc_library(
  name = "status",
  hdrs = ["status.h"],
  srcs = ["status.cc"],
  deps = [
    "//third_party/glog",
  ]
)

cc_library(
  name = "util",
  visibility = ["//visibility:public"],
  deps = [
    ":status",
  ]
)
