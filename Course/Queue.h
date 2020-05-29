#pragma once
template<typename T>
class Queue;

template<typename T>
class NodeList {
private:
	T value;
	NodeList *next;
	NodeList *prev;
public:
	explicit NodeList(T value = T(), NodeList *next = nullptr, NodeList *prev = nullptr) {
		this->value = value;
		this->next = next;
		this->prev = prev;
	}
	friend class Queue<T>;
	
};

using namespace std;

template<typename T>
class Queue {
	size_t queueSize{};
public:
	NodeList<T> *head;
	NodeList<T> *last;

	Queue() {
		head = last = nullptr;
	}

	~Queue() {
		while (queueSize) {
			dequeue();
		}
	}

	void enqueue(T value) {
		if (head == nullptr) {
			head = new NodeList<T>(value);
			last = head;
		}
		else {
			auto *Cur = new NodeList<T>(value, last);
			last->prev = Cur;
			Cur = last;
			last = last->prev;
			last->next = Cur;
		}
		queueSize++;
	}

	void dequeue() {
		if (!queueSize) throw out_of_range("Exception!");
		else {
			if (head == last) {
				delete head;
				head = last = nullptr;
			}
			else {
				head = head->prev;
				delete head->next;
				head->next = nullptr;
			}
			queueSize--;
		}
	}

	T peek() {
		if (!queueSize) throw out_of_range("Exception!");
		else {
			return head->value;
		}
	}

	size_t size() {
		return queueSize;
	}
};