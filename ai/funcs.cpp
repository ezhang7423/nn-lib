#pragma once
#include "../library.cpp"

using namespace std;

listf softmax(listf x) {
  float max = *max_element(begin(x), end(x));
  listf res;
  for (auto &&i : x) {
    res.push_back(exp(i - max));
  }
  float sum = 0;
  for (auto &&i : res) {
    sum += i;
  }
  for (auto &&i : res) {
    i /= sum;
  }
  return res;
}

template <typename T> std::vector<T> arange(T start, T stop, T step = 1) {
  std::vector<T> values;
  for (T value = start; value < stop; value += step)
    values.push_back(value);
  return values;
}

mat broadcast(list a, list b) {
  // mat *res = new mat(b.size(), a.size());
  mat res(b.size(), a.size());
  for (unsigned i = 0; i < b.size(); i++) {
    for (unsigned j = 0; j < a.size(); j++) {
      res(i, j) = b[i] + a[j];
    }
  }
  return res;
};
mat reshape(list rp, int width, int height) {
  if (width == -1) {
    width = rp.size() / height;
  } else if (height == -1) {
    height = rp.size() / width;
  }
  mat res(height, width);
  int j = 0;
  for (auto i : rp) {
    // cout << (to_string(i)) << endl;
    int r = j / width;
    int c = j % width;
    res(r, c) = i;
    j++;
  }
  return res;
};
list repeat(list rp, int num) {
  list res(rp.size() * num);
  int j = 0;
  for (auto &&i : res) {
    i = rp[j / num];
    j++;
  }
  return res;
}

list tile(list rp, int num) {
  list res(rp.size() * num);
  int j = 0;
  for (auto &&i : res) {
    i = rp[j % rp.size()];
    j++;
  }
  return res;
}
