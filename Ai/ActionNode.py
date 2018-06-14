#!/usr/bin/env python
# coding: utf-8

from Client import Client


def look(client: Client, args):
    client.build_command("Look")
    print("je vais look")
    return 1


def CheckingFood():
    pass


def node_action0(client: Client, args):
    print("Je suis l'action d'id %d" % args[0])
    return 0


class ActionNode:
    def __init__(self, node_id: int, func):
        self.id = node_id
        self.func = func

    def action(self, client: Client, args) -> int:
        return self.func(client, args)
