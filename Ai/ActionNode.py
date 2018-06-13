#!/usr/bin/env python
# coding: utf-8


def node_action0():
    return 0

class ActionNode:
    def __init__(self, node_id: int, func):
        self.id = node_id
        self.func = func

    def action(self):
        self.func()
        return self.id

