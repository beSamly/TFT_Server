#pragma once
struct PacketHeader {
  int size;
  int prefix;
  int id;  // ��������ID (ex. 1=�α���, 2=�̵���û)
};
