#ifndef UTIL_STATUS_H_
#define UTIL_STATUS_H_

#include <string>
#include <sstream>
#include <system_error>

namespace util {

class __attribute__((warn_unused_result)) Status {
public:
  // Represents OK status.
  Status() {}

  bool ok() const {
    return error_code_.value() == 0;
  }

  std::error_code error_code() const {
    return error_code_;
  }

  std::string error_message() const {
    return error_message_;
  }

  static const Status& OK;

private:
  Status(const std::error_code& code, const std::string& message)
    : error_code_(code), error_message_(message) {}

  std::error_code error_code_;
  std::string error_message_;

  friend class StatusBuilder;
};

class StatusBuilder {
public:
  explicit StatusBuilder(std::error_code error)
    : error_code_(error) {}

  explicit StatusBuilder(std::errc error)
    : error_code_(std::make_error_code(error)) {}

  template<typename T>
  StatusBuilder& operator<<(T& v) {
    error_message_stream_ << v;
    return *this;
  }

  StatusBuilder& operator<<(char* v) {
    error_message_stream_ << v;
    return *this;
  }

  operator Status() {
    return Status(error_code_, error_message_stream_.str());
  }

private:
  std::error_code error_code_;
  std::ostringstream error_message_stream_;
};

#define RETURN_OK() return ::util::Status()
#define RETURN_ERROR(errc) return ::util::StatusBuilder((errc))

} // namespace util

#endif // UTIL_STATUS_H_
