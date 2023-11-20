// 观察者模式
//
#include <iostream>
#include <vector>

class Subject;
class Observer {
 public:
  virtual void Update() = 0;

 protected:
  std::shared_ptr<Subject> subject_;
};

class Subject {
 public:
  int GetState() { return state_; }

  void SetState(int state) {
    state_ = state;
    NotifyAllObservers();
  }

  void AttachObserver(const std::shared_ptr<Observer>& observer) {
    observers_.emplace_back(observer);
  }

  void NotifyAllObservers() {
    for (const auto& observer : observers_) {
      observer->Update();
    }
  }

 private:
  int state_;
  std::vector<std::shared_ptr<Observer>> observers_;
};

class BinaryObserver : public Observer,
                       public std::enable_shared_from_this<BinaryObserver> {
 public:
  std::shared_ptr<BinaryObserver> GetPtr() { return shared_from_this(); }

  void RegisterSubject(std::shared_ptr<Subject>& subject) {
    subject_ = subject;
    subject_->AttachObserver(GetPtr());
  }

  virtual void Update() {
    std::cout << "Binary String: " << subject_->GetState() << std::endl;
  }
};

class OctalObserver : public Observer,
                      public std::enable_shared_from_this<OctalObserver> {
 public:
  std::shared_ptr<OctalObserver> GetPtr() { return shared_from_this(); }

  void RegisterSubject(std::shared_ptr<Subject>& subject) {
    subject_ = subject;
    subject_->AttachObserver(GetPtr());
  }

  void Update() {
    std::cout << "Octal String: " << subject_->GetState() << std::endl;
  }
};

class HexaObserver : public Observer,
                     public std::enable_shared_from_this<HexaObserver> {
 public:
  std::shared_ptr<HexaObserver> GetPtr() { return shared_from_this(); }

  void RegisterSubject(std::shared_ptr<Subject>& subject) {
    subject_ = subject;
    subject_->AttachObserver(GetPtr());
  }

  void Update() {
    std::cout << "Hexa String: " << subject_->GetState() << std::endl;
  }
};

int main(void) {
  auto subject = std::make_shared<Subject>();
  auto binary_observer = std::make_shared<BinaryObserver>();
  binary_observer->RegisterSubject(subject);
  auto octal_observer = std::make_shared<OctalObserver>();
  octal_observer->RegisterSubject(subject);
  auto hexa_observer = std::make_shared<HexaObserver>();
  hexa_observer->RegisterSubject(subject);

  std::cout << "First change: " << std::endl;
  subject->SetState(15);
  std::cout << "Second change: " << std::endl;
  subject->SetState(10);

  return 0;
}

